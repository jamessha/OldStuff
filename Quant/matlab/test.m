function [R] = test()
    R = [1 2 3; 4 5 6; 7 8 9; 1 2 3; 4 5 6; 7 8 9; 1 2 3; 4 5 6; 7 8 9];
    tickers = ['a'; 'b'; 'c'; 'd'; 'e'; 'f'; 'g'; 'h'; 'j'];
    tickers1 = ['a'; 'b'; 'e'; 'f'; 'h'];

    function [R] = ticker_filter(R, tickers, tickers1)
            if isempty(tickers1)
                R = [];
            elseif strcmp(tickers1(1), tickers(1))
                R = [R(1, :); ticker_filter(R(2:end, :), tickers(2:end), tickers1(2:end))];
            else
                [R] = ticker_filter(R(2:end, :), tickers(2:end), tickers1);
            end
    end

        [R] = ticker_filter(R, tickers, tickers1);

end