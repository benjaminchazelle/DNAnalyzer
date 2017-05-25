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

	var response = "";

	var client = new net.Socket();
	client.connect(PORT, SERVER, function() {			
		client.write(request);
	});

	client.on('data', function(data) {
		response += data.toString();
	});

	client.on('close', function() {
		
		if(response == expectedResponse) {
			
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