%% Thingspeak Upload Script
clc;
clear;

%% Run Simulink Model (IMPORTANT: change model name)
modelName = 'Likitha_Version_10';   % <-- replace with your model name
out = sim(modelName);

%% Extract Data
data = out.data32;

%% Channel Details
channel1 = 3301782;
key1 = 'JKLKCO8AK0MRW4CW';

channel2 = 3301835;
key2 = 'E7OOJBGDEHIK4XA5';

channel3 = 3301844;
key3 = 'GAFKA45LYKNR0V7R';

channel4 = 3301854;
key4 = 'S4690KBYUG75SLYN';

%% Upload Loop
for i = 1:size(data,1)

    fprintf('Uploading row %d...\n', i);

    % Channel 1 (1–8)
    thingSpeakWrite(channel1, data(i,1:8), 'WriteKey', key1);
    pause(15);

    % Channel 2 (9–16)
    thingSpeakWrite(channel2, data(i,9:16), 'WriteKey', key2);
    pause(15);

    % Channel 3 (17–24)
    thingSpeakWrite(channel3, data(i,17:24), 'WriteKey', key3);
    pause(15);

    % Channel 4 (25–32)
    thingSpeakWrite(channel4, data(i,25:32), 'WriteKey', key4);
    pause(15);

end

disp('✅ Data upload completed successfully!');