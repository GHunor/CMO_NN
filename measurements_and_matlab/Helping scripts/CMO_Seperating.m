function [glove, myo, opt1, opt2, opt3] = CMO_Seperating(progdata)
%CMO_Seperating Seperates the data into the sensors it come from

rds = CMO_rawdataseperator()


for i = 1:size(progdata, 1)
    base = progdata{i,6}(:,rds);
    myo{i} = base(:,1:8);
    glove{i} = base(:,9:31);
    opt1{i}= base(:,32:34);
    opt2{i}= base(:,35:37);
    opt3{i}= base(:,38:40);
end

end