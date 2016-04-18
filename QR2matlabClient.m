addpath(genpath('~/openrobots/lib/matlab'));

client = genomix.client;
QR2matlab = client.load('QR2matlab');
connection = QR2matlab.connect_port('dataIn', '/visp_auto_tracker/code_message');

publish = QR2matlab.Publish('-a',10);

while(1)
    result = QR2matlab.dataOut();
    disp(result.dataOut.message.data);
    pause(0.1);
end