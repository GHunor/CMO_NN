function [Odata , ret] = CMO_OptShift(op, bias, PreT1, PreT3, PreVS, starter, MT, T, EUMdata, S)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    Ot = op(:,1);
    
    Od = op(:,2:end);
    [Ot, ~, ~] = CMO_Time_overflow_corrector(Ot, 65535, bias, PreT1);
    if sort(Ot)~=Ot
        display('Ot not sorted')
        Ot
        figure
        plot(1:size(Ot,1), Ot)
    end
    Ot = Ot - starter + 1;
    LI = CMO_time_skip_detect([PreT3;Ot],10, 0.1);
    %Syncronize
    OTi = [PreT3;Ot];

    Inds = (1:size(MT, 1))';
    SyncPs = Inds(LI==1, 1);
    if length(SyncPs) == 0
        MaxD = length(OTi)*0.2
    else
        SyncP = SyncPs(1);
        MaxD = OTi(SyncP)-min(OTi);
    end
    BestOD =[];
    Bret = 0;
    Bshift = 0;
    ShiftsO = [];
    BNL = [];
    BNLL = {}
    inL = 1;
    sNLVm = 0;

    OTi = OTi-S;
    TInterval = CMO_IntervalFromDetect(OTi, LI, PreT3, OTi(end,1));
    TSN = CMO_FixPointTSNGen(0, 0,max(OTi)+S, T);
    TSN = TSN';

    [ndata] = CMO_Interp1PartWT(Od, OTi(2:end), TSN, PreVS, OTi(1));
    [LV] = CMO_IntervalToInclude(TSN, TInterval);
    %LV = LV'
    EUOdata = CMO_Metric_Euc(ndata);

    size(MT, 1)
    size(EUMdata, 1)

    if size(EUOdata, 1)<size(EUMdata, 1)
        Zer = zeros(size(MT, 1), 3);
        One = ones(size(MT, 1), 1);
        H1 = 1:length(TSN);
        H2 = H1(TSN==0);
        H3 = 1:length(MT);
        H4 = H3(MT==0);
        IC = H4-H2;

        NEUOdata =  Zer(:,1);
        NEUOdata(H1+IC) = EUOdata;

        Odata = Zer;
        Odata(H1+IC, :) = ndata;

        NLV = Zer(:,1);
        NLV(H1+IC) = LV;
        NLV = NLV & One;
        Odata(:, 4) = NLV;
    else
        display('Op data somehow longer than MT')
    end
    Dat = [EUMdata,NEUOdata];
    [List1] = CMO_SepByLindex(Dat, NLV);
    [ret] = CMO_ListCORRCheck(List1);
end