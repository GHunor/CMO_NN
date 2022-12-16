function [rds] = CMO_rawdataseperator()
%A set of indexes that cuts out only the raw date without timestamps
%index, movement_code, cpu_time, myo_time, myo_data(8), glove_time, glove_data(22), opt1_time, opt1_data(3), opt2_time, opt2_data(3), opt3_time, opt3_data(3)
rds = [5:12, 14:36, 38:40, 42:44, 46:48];
end

