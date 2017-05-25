// Author : Benjamin CHAZELLE
// Licence MIT

const spawn = require("child_process").spawn;
const fs = require("fs");
const net = require("net");

EXE = "../Debug/DNAnalyzerServer.exe";
TEST_DIR = ".";

SERVER = "127.0.0.1";
PORT = 8282;

REQUEST_FILENAME = "requete.txt";
RESPONSE_FILENAME = "reponse.txt";

serverProcess = spawn(EXE, ['-d', '../NetworkTest/dictionnaire.dico']);

serverProcess.on('error', function (e) {
	if(e.errno == "ENOENT") {
		console.log("Error : file " + EXE + " can't be reached");
	} else {
		console.log("Error : " + e.errno)
	}
	process.exit(1);
});


serverProcess.on('exit', function (code) {
	if(code != 0) {
		console.log("Error : program returns " + code)
		// process.exit(1);
	}	
});


allTests = [];
failedTests = [];

function doTest(testTitle) {	
	
	var request = fs.readFileSync(testTitle + "/" + REQUEST_FILENAME).toString();
	var expectedResponse = fs.readFileSync(testTitle + "/" + RESPONSE_FILENAME).toString();

	var expectedResponseUnordered = fs.existsSync(testTitle + "/" + "unordered." + RESPONSE_FILENAME);
	
	var response = "";

	var client = new net.Socket();
	client.connect(PORT, SERVER, function() {			
		client.write(request);
	});

	client.on('data', function(data) {
		response += data.toString();
	});

	client.on('close', function() {
		
		var match = response == expectedResponse;
		
		if(! match && expectedResponseUnordered) {
			
			// Vérifier si les lignes attendues (et seuelment elles) sont toutes là, qu'importe l'ordre
			
			var unordered = JSON.parse(fs.readFileSync(testTitle + "/" + "unordered." + RESPONSE_FILENAME).toString());
			
			var expectedResponseSplit = expectedResponse.split(unordered.separator);
			
			if(unordered.end == "$end") {
				unordered.end = expectedResponseSplit.length;
			}
			
			var expectedFragments = {};
			
			for(var i in expectedResponseSplit) {
				
				if(i < unordered.start) {
					continue;
				}
				if(i > unordered.end) {
					break;
				}
				
				const split = expectedResponseSplit[i];
				
				if(split in expectedFragments) {
					expectedFragments[split]++;
				} else {
					expectedFragments[split] = 1;
				}
			}

			var elapsedResponseSplit = response.split(unordered.separator);
			
			var elapsedFragments = {};
			
			for(var i in elapsedResponseSplit) {
				
				if(i < unordered.start) {
					continue;
				}
				if(i > unordered.end) {
					break;
				}
				
				const split = elapsedResponseSplit[i];
				
				if(split in elapsedFragments) {
					elapsedFragments[split]++;
				} else {
					elapsedFragments[split] = 1;
				}
			}				
			
			for(var i in expectedFragments) {
				
				if(  (i in elapsedFragments && elapsedFragments[i] == expectedFragments[i]) ) {
					delete elapsedFragments[i];
				}
				
			}
			
			match = Object.keys(elapsedFragments).length == 0;			
			
		}
		
		if(match) {
			
			console.log("OK Test " + testTitle)
			
		} else {
			
			console.log("!! Test " + testTitle)
			console.log("== Request ==");
			// console.log(request.replace(/\r\n/g, "\\r\\n\n"));
			console.log("== Response ==");
			console.log(response.replace(/\r\n/g, "\\r\\n\n"));
			console.log("== Excepted response ==");
			console.log(expectedResponse.replace(/\r\n/g, "\\r\\n\n"));
			console.log("=======================")
			console.log("")
		}
		
		if(allTests.length > 0) {
			nextTestTitle = allTests.pop();
			doTest(nextTestTitle);	
			//console.log("?? Test " + nextTestTitle)
			
			if(allTests.length == 0) {
				process.exit(0);
			}
		}
	});	
	
}

setTimeout(function () {
	

for(item of fs.readdirSync(TEST_DIR)) {
	
	if(fs.existsSync(item + "/" + REQUEST_FILENAME) && fs.existsSync(item + "/" + RESPONSE_FILENAME)) {
		
		allTests.push(item);

	}
	
}

if(allTests.length > 0) {
	doTest(allTests.pop());
}

// console.log();
}, 500);