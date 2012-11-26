function [tickers, cov_matrix] = covariance(tickers_er, source)
    e = actxserver('Excel.Application');
    workbook = e.workbooks.Open(sprintf('E:\\Dropbox\\Projects\\Quant\\data\\%s', source));
    num_sheets = workbook.Sheets.Count - 1;
    min_hist = 1000;

    %Finding the minimum length of history
    for i = 1:num_sheets
        sheet = workbook.Sheets.Item(i);
        data = sheet.UsedRange.Value;
        adjusted = data(:, 4);
        len_hist = length(adjusted);
        if len_hist < min_hist
            min_hist = len_hist;
        end
    end
    
    %Predefining
    R = zeros(min_hist-3, num_sheets); 
    tickers = cell(num_sheets, 1); 
    
    %Finding the historical returns
    for i = 1:num_sheets
        sheet = workbook.Sheets.Item(i);
        data = sheet.UsedRange.Value;
        returns = zeros(min_hist-1, 1); %Predefining
        ticker = data(2, 1);
        adjusted = cell2mat(data(2:min_hist, 4));
        for j = 3:(min_hist-200) %Redefine to adjust how much history is seen
            rr = (adjusted(j)-adjusted(j-1))/adjusted(j-1); %((return - capital)/capital)
            returns(j, 1) = rr;
        end
        returns = returns(3:end);
        R(:, i) = returns;
        tickers(i, 1) = ticker;
    end
    
    %Cleanup
    workbook.Close
    
    %Recursive filtering of R for tickers lost due to data errors in the
    %expected returns
    set(0, 'RecursionLimit', 750)
    function [R] = ticker_filter(R, tickers, tickers1)
            if isempty(tickers1) || isempty(tickers)
                R = [];
            elseif strcmp(tickers1(1), tickers(1))
                R = [R(:, 1); ticker_filter(R(:, 2:end), tickers(2:end), tickers1(2:end))];
            else
                [R] = ticker_filter(R(:, 2:end), tickers(2:end), tickers1);
            end
    end

    R = ticker_filter(R, tickers, tickers_er);

    cov_matrix = cov(R);
    
    
end