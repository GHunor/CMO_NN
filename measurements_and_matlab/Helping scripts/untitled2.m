clear;
close all;

directory = 'test2';
mkdir(directory)
num = 10
num2 = 10

a = 1:10
Mat = a'*a
formatSpec = "%s/%d_%d__blabla.txt"
sprintf(formatSpec,directory, 1,1)
for i =1:num
    for k = 1:num2
        writematrix(Mat, sprintf(formatSpec, directory, i,k))
        pause(1)
    end
    pause(1)
end