%% Simulation to CSV Export Script
clc;
clear;

%% Step 1: Run Simulink Model (change model name)
modelName = 'Likitha_Version_10';   % <-- Replace with your model
out = sim(modelName);

%% Step 2: Extract Data
data = out.data32;

%% Step 3: Define Headers (32 parameters)
headers = [ ...
    "V_sim","I_sim","SOC_sim","SOH_sim","T_sim","RUL_sim","health_idx_sim", ...
    "V_hw","I_hw","SOC_hw","SOH_hw","T_hw","RUL_hw","health_idx_hw", ...
    "V_diff","I_diff","SOC_diff","SOH_diff","T_diff","RUL_diff", ...
    "RMSE_V","RMSE_I","RMSE_SOC","RMSE_SOH", ...
    "imbalance_sim","imbalance_hw","charging_eff","coulombic_eff", ...
    "algo_sim","algo_hw","stress_idx_sim","stress_idx_hw" ...
];

%% Step 4: Convert to Table
T = array2table(data, 'VariableNames', headers);

%% Step 5: Save to CSV
fileName = 'output.csv';
writetable(T, fileName);

%% Step 6: Confirmation
disp(['✅ CSV file created successfully: ', fileName]);