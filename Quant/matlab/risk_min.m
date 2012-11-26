function [tickers_er, w, risk, returns, shares, sigma_expected, u_expected] = risk_min(capital)
    source_er = 'current.xlsx';
    source_cov = 'historical.xlsx';
    risk_free = 0.00;
    
    % Expected Returns
    [prices, tickers_er, u] = expected_returns(source_er);
    
    % Covariance
    [~, cov] = covariance(tickers_er, source_cov);
    
    % l vector
    [x_size, ~] = size(tickers_er);
    l = ones(x_size, 1);
    
    % Plotting efficient frontier
    x = [];
    
    for u0 = 0:0.001:0.15
        cvx_begin
            cvx_quiet(true)
            variable w(x_size)
            minimize (w'*cov*w)
            subject to
                w'*u == u0
                w'*l == 1
        cvx_end;
        
        x = [x w];
    end
    
    u_expected = []; %Expected Returns
    sigma_expected = []; %Expected Risk
    
    for column = x
        u_expected = [u_expected column'*u];
        sigma_expected = [sigma_expected (column'*cov*column)^.5];
    end
    
    plot(sigma_expected, u_expected)
    
    % Minimizing risk
    [~, y] = size(sigma_expected);
    i = 1;
    for i_new = 1:y
        if sigma_expected(i_new) < sigma_expected(i)
            i = i_new;
        end
    end
    risk = sigma_expected(i);
    returns = u_expected(i);
    
    cvx_begin
        cvx_quiet(true)
        variable w(x_size)
        minimize (w'*cov*w)
        subject to
            w'*u == risk
            w'*l == 1
    cvx_end;
    
    % Finding # of shares
    shares = cell(length(tickers_er), 2);
    for i = 1:length(tickers_er)
        num_shares = floor(capital*w(i)/prices(i));
        shares(i, 1) = tickers_er(i);
        shares{i, 2} = num_shares;
    end

    
end
        
        