addpath(genpath('~/openrobots/lib/matlab'));

client = genomix.client;
QR2matlab = client.load('QR2matlab');
QR2matlab.connect_port('dataIn', '/visp_auto_tracker/code_message' );
p = 3;

publish = QR2matlab.Publish('-a');

while(1)
    result = QR2matlab.dataOut();
    disp(result.dataOut.message);
    pause(0.1);
end