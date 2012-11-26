function [price_vector, tickers, er_vector] = expected_returns(source)
    e = actxserver('Excel.Application');
    workbook = e.workbooks.Open(sprintf('E:\\Dropbox\\Projects\\Quant\\data\\%s', source));
    num_sheets = workbook.Sheets.Count - 1;
    
    g = 0.039; % nominal GDP growth rate
    tickers = [];
    er_vector = [];
    price_vector = [];
    
    for i = 1:num_sheets
        sheet = workbook.Sheets.Item(i);
        data = sheet.UsedRange.Value;
        ce = cell2mat(data(2, 9)); %current earnings per share
        cpeg = cell2mat(data(2, 6)); %current price/earnings to growth
        cpe = cell2mat(data(2, 15)); %current price/earnings 
        b = cell2mat(data(2, 21)); %book value per share
        p = cell2mat(data(2, 8)); %current price
        if isa(cpeg, 'double') && isa(cpe, 'double') && isa(b, 'double') && isa(p, 'double')
            tickers = [tickers; data(2, 1)];
            eeg = cpe/cpeg; %expected earnings growth rate in percent
            e = ce*(1 + eeg/100); %expected earnings = current earnings per share * expected earnings growth
            er = (e-g*b)/p + g;
            er_vector = [er_vector; er];
            price_vector = [price_vector p];
        end;
    end;
    
    workbook.Close;
end