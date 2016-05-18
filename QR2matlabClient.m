addpath(genpath('~/openrobots/lib/matlab'));
p=0.2;

client = genomix.client;
pause(p);
QR2matlab = client.load('QR2matlab');
pause(p);
QR2matlab.connect_port('messageIn', '/visp_auto_tracker/code_message' );
pause(p);
QR2matlab.connect_port('poseIn', '/visp_auto_tracker/object_position' );
pause(p);

publish = QR2matlab.Publish('-a');


qrcode = QR2matlab.dataOut(); % repet as many times you want

% stop = QR2matlab.Stop();
% kill = QR2matlab.kill();
