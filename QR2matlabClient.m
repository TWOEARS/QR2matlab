addpath(genpath('~/openrobots/lib/matlab'));

client = genomix.client;
QR2matlab = client.load('QR2matlab');
QR2matlab.connect_port('dataIn', '/visp_auto_tracker/code_message' );

publish = QR2matlab.Publish(10);

result = QR2matlab.dataOut();
disp(result.dataOut.message.data);

stop = QR2matlab.Stop();
kill = QR2matlab.kill();
