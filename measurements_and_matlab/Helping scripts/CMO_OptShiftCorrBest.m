function [ OPFD2, OPFT2, OPFT3, ShiftsO, Bshift] = CMO_OptShiftCorrBest(op, bias, PreT1, PreT3, PreVS, starter, MT, T, EUMdata)
    
    Ot = op(:,1);
    
    Od = op(:,2:end);
    [Ot, bias, ~] = CMO_Time_overflow_corrector(Ot, 65535, bias, PreT1);

    figure
    plot(Ot)

    OPFT2 = Ot;
    OPFD2 = Od;
    if sort(Ot)~=Ot
        display('Ot not sorted')
        Ot
        figure
        plot(1:size(Ot,1), Ot)
    end
    Ot = Ot - starter + 1;
    OPFT3 = Ot;
    LI = CMO_time_skip_detect([PreT3;Ot],10, 0.1);
    OPFT3 = [OPFT3, LI(2:end)];
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
    BNLL = {};
    inL = 1;
    sNLVm = 0;
    %figure
    %hold on
    %plot(MT, zeros(size(MT, 1), 1), 'ro')
    OTiO = OTi;
    for i = 0:MaxD
        
        OTi = OTiO-i;
        TInterval = CMO_IntervalFromDetect(OTi, LI, PreT3, OTi(end,1));
        TSN = CMO_FixPointTSNGen(0, 0,max(OTi)+i, T);
        TSN = TSN';
        %if i/100 == floor(i/100)
            %plot([min(OTi),max(OTi)], [1+i/MaxD, 1+i/MaxD], 'go')
            %plot([min(TSN),max(TSN)], [2+i/MaxD, 2+i/MaxD], 'bo')
        %end
        [ndata] = CMO_Interp1PartWT(Od, OTi(2:end), TSN, PreVS, OTi(1));
        [LV] = CMO_IntervalToInclude(TSN, TInterval);
        %LV = LV'
        EUOdata = CMO_Metric_Euc(ndata);
        if size(EUOdata, 1)<size(EUMdata, 1)
            Zer = zeros(size(MT, 1), 1);
            One = ones(size(MT, 1), 1);
            H1 = 1:length(TSN);
            H2 = H1(TSN==0);
            H3 = 1:length(MT);
            H4 = H3(MT==0);
            IC = H4-H2;
            NEUOdata =  Zer;
            NEUOdata(H1+IC) = EUOdata;
            NLV = Zer;
            NLV(H1+IC) = LV;
            NLV = NLV & One;
            if i == 0
                sNLVm = sum(NLV);
            end
        else
            display('Op data somehow longer than MT')
        end
        Dat = [EUMdata,NEUOdata];
        [List1] = CMO_SepByLindex(Dat, NLV);
        [ret] = CMO_ListCORRCheck(List1);
        if length(ret) == 0
            ret = 0
        end
        ShiftsO(i+1, 1) = i;
        ShiftsO(i+1, 2) = ret;
        ShiftsO(i+1, 3) = sum(NLV);
    end
end