% w is the weight vector, u is expected returns, cov is covariance matrix

u = [.079; 
    .079; 
    .09; 
    .071];

cov = [.195^2 .24*.195*.182 .25*.195*.183 .22*.165*.195;
    .24*.182*.195 .182^2 .47*.182*.183 .14*.182*.165
    .25*.195*.183 .47*.182*.183 .183^2 .25*.183*.165
    .22*.195*.165 .14*.182*.165 .25*.183*.165 .165^2];

l = [1;
    1;
    1;
    1];

%{
u0 = 0.078;

cvx_begin
    variable w(4)
    minimize(w'*cov*w)
    subject to
        w'*u == u0
        w'*l == 1
cvx_end
%}

% Plotting
x = [];

for u0 = 0.05:0.001:0.12
    cvx_begin
        cvx_quiet(true)
        variable w(4)
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

