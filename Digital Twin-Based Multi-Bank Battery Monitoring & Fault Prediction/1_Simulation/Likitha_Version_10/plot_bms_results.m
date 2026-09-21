%% MATLAB Script to Plot Digital Twin BMS Results from CSV
% Clear workspace and close all figures
clear; close all; clc;

% Read the CSV file (adjust filename if needed)
filename = 'output.csv';   % change to your actual file name
data = readtable(filename);

% Extract time vector (if not present, create one based on row count)
% Assuming each row is a time step; create a time vector in seconds
t = (0:height(data)-1)';   % time in samples (or use actual time if available)

%% 1. Simulation vs Hardware – Core Parameters
figure('Name', 'Simulation vs Hardware Comparison', 'Position', [100 100 1200 800]);

% Voltage
subplot(3,3,1);
plot(t, data.V_sim, 'b-', 'LineWidth', 1.5); hold on;
plot(t, data.V_hw, 'r--', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('Voltage (V)');
title('Voltage: Sim vs HW');
legend('Sim', 'HW', 'Location', 'best');
grid on;

% Current
subplot(3,3,2);
plot(t, data.I_sim, 'b-', 'LineWidth', 1.5); hold on;
plot(t, data.I_hw, 'r--', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('Current (A)');
title('Current: Sim vs HW');
legend('Sim', 'HW', 'Location', 'best');
grid on;

% SOC
subplot(3,3,3);
plot(t, data.SOC_sim, 'b-', 'LineWidth', 1.5); hold on;
plot(t, data.SOC_hw, 'r--', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('SOC (%)');
title('State of Charge');
legend('Sim', 'HW', 'Location', 'best');
grid on;

% SOH
subplot(3,3,4);
plot(t, data.SOH_sim, 'b-', 'LineWidth', 1.5); hold on;
plot(t, data.SOH_hw, 'r--', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('SOH (%)');
title('State of Health');
legend('Sim', 'HW', 'Location', 'best');
grid on;

% Temperature
subplot(3,3,5);
plot(t, data.T_sim, 'b-', 'LineWidth', 1.5); hold on;
plot(t, data.T_hw, 'r--', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('Temperature (°C)');
title('Temperature');
legend('Sim', 'HW', 'Location', 'best');
grid on;

% RUL
subplot(3,3,6);
plot(t, data.RUL_sim, 'b-', 'LineWidth', 1.5); hold on;
plot(t, data.RUL_hw, 'r--', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('RUL (cycles)');
title('Remaining Useful Life');
legend('Sim', 'HW', 'Location', 'best');
grid on;

% Health Index
subplot(3,3,7);
plot(t, data.health_idx_sim, 'b-', 'LineWidth', 1.5); hold on;
plot(t, data.health_idx_hw, 'r--', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('Health Index');
title('Overall Health Index');
legend('Sim', 'HW', 'Location', 'best');
grid on;

% Stress Index
subplot(3,3,8);
plot(t, data.stress_idx_sim, 'b-', 'LineWidth', 1.5); hold on;
plot(t, data.stress_idx_hw, 'r--', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('Stress Index');
title('Stress Index');
legend('Sim', 'HW', 'Location', 'best');
grid on;

% Cell Imbalance
subplot(3,3,9);
plot(t, data.imbalance_sim, 'b-', 'LineWidth', 1.5); hold on;
plot(t, data.imbalance_hw, 'r--', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('Imbalance (V)');
title('Cell Voltage Imbalance');
legend('Sim', 'HW', 'Location', 'best');
grid on;

%% 2. Differences and Errors
figure('Name', 'Differences and Errors', 'Position', [100 100 1200 600]);

% Voltage difference
subplot(2,4,1);
plot(t, data.V_diff, 'k-', 'LineWidth', 1);
xlabel('Time (samples)'); ylabel('ΔV (V)');
title('Voltage Difference');
grid on; yline(0, 'r--');

% Current difference
subplot(2,4,2);
plot(t, data.I_diff, 'k-', 'LineWidth', 1);
xlabel('Time (samples)'); ylabel('ΔI (A)');
title('Current Difference');
grid on; yline(0, 'r--');

% SOC difference
subplot(2,4,3);
plot(t, data.SOC_diff, 'k-', 'LineWidth', 1);
xlabel('Time (samples)'); ylabel('ΔSOC (%)');
title('SOC Difference');
grid on; yline(0, 'r--');

% SOH difference
subplot(2,4,4);
plot(t, data.SOH_diff, 'k-', 'LineWidth', 1);
xlabel('Time (samples)'); ylabel('ΔSOH (%)');
title('SOH Difference');
grid on; yline(0, 'r--');

% RMSE Voltage
subplot(2,4,5);
plot(t, data.RMSE_V, 'm-', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('RMSE (V)');
title('RMSE Voltage');
grid on;

% RMSE Current
subplot(2,4,6);
plot(t, data.RMSE_I, 'm-', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('RMSE (A)');
title('RMSE Current');
grid on;

% RMSE SOC
subplot(2,4,7);
plot(t, data.RMSE_SOC, 'm-', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('RMSE (%)');
title('RMSE SOC');
grid on;

% RMSE SOH
subplot(2,4,8);
plot(t, data.RMSE_SOH, 'm-', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('RMSE (%)');
title('RMSE SOH');
grid on;

%% 3. Efficiency and Algorithm Usage
figure('Name', 'Efficiency & Algorithms', 'Position', [100 100 1000 400]);

% Charging and Coulombic efficiency
subplot(1,3,1);
plot(t, data.charging_eff, 'g-', 'LineWidth', 1.5); hold on;
plot(t, data.coulombic_eff, 'b--', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('Efficiency');
title('Efficiencies');
legend('Charging', 'Coulombic', 'Location', 'best');
grid on; ylim([0 2]);

% Algorithm codes
subplot(1,3,2);
stairs(t, data.algo_sim, 'b-', 'LineWidth', 1.5); hold on;
stairs(t, data.algo_hw, 'r--', 'LineWidth', 1.5);
xlabel('Time (samples)'); ylabel('Algorithm Code');
title('Active Algorithm');
legend('Sim', 'HW', 'Location', 'best');
yticks(1:5);
ylim([0 6]);
grid on;

% Stress indices difference (optional)
subplot(1,3,3);
plot(t, data.stress_idx_sim - data.stress_idx_hw, 'k-', 'LineWidth', 1);
xlabel('Time (samples)'); ylabel('Δ Stress');
title('Stress Index Difference');
grid on; yline(0, 'r--');

%% 4. Statistical Summary (Histograms of Errors)
figure('Name', 'Error Distributions', 'Position', [100 100 1000 600]);

subplot(2,3,1);
histogram(data.V_diff, 30, 'FaceColor', [0.2 0.6 0.8]);
xlabel('Voltage Error (V)'); ylabel('Frequency');
title('Voltage Error Distribution');
grid on;

subplot(2,3,2);
histogram(data.I_diff, 30, 'FaceColor', [0.2 0.8 0.6]);
xlabel('Current Error (A)'); ylabel('Frequency');
title('Current Error Distribution');
grid on;

subplot(2,3,3);
histogram(data.SOC_diff, 30, 'FaceColor', [0.8 0.4 0.2]);
xlabel('SOC Error (%)'); ylabel('Frequency');
title('SOC Error Distribution');
grid on;

subplot(2,3,4);
histogram(data.SOH_diff, 30, 'FaceColor', [0.8 0.2 0.6]);
xlabel('SOH Error (%)'); ylabel('Frequency');
title('SOH Error Distribution');
grid on;

subplot(2,3,5);
histogram(data.RMSE_SOC, 30, 'FaceColor', [0.5 0.5 0.9]);
xlabel('RMSE SOC (%)'); ylabel('Frequency');
title('RMSE SOC Distribution');
grid on;

subplot(2,3,6);
histogram(data.RMSE_SOH, 30, 'FaceColor', [0.9 0.6 0.2]);
xlabel('RMSE SOH (%)'); ylabel('Frequency');
title('RMSE SOH Distribution');
grid on;

%% 5. Summary Statistics Print
fprintf('\n========== SUMMARY STATISTICS ==========\n');
fprintf('Mean Voltage Error: %.4f V\n', mean(data.V_diff));
fprintf('Mean Current Error: %.4f A\n', mean(data.I_diff));
fprintf('Mean SOC Error: %.4f %%\n', mean(data.SOC_diff));
fprintf('Mean SOH Error: %.4f %%\n', mean(data.SOH_diff));
fprintf('Final RMSE Voltage: %.4f V\n', data.RMSE_V(end));
fprintf('Final RMSE Current: %.4f A\n', data.RMSE_I(end));
fprintf('Final RMSE SOC: %.4f %%\n', data.RMSE_SOC(end));
fprintf('Final RMSE SOH: %.4f %%\n', data.RMSE_SOH(end));
fprintf('Mean Charging Efficiency: %.4f\n', mean(data.charging_eff));
fprintf('Mean Coulombic Efficiency: %.4f\n', mean(data.coulombic_eff));
fprintf('Algorithm used most (sim): %d\n', mode(data.algo_sim));
fprintf('Algorithm used most (hw): %d\n', mode(data.algo_hw));
fprintf('========================================\n');

disp('All plots generated successfully.');