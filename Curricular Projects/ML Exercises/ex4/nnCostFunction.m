function [J grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices. 
% 
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

% Setup some useful variables
m = size(X, 1);
         
% You need to return the following variables correctly 
J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m
%
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a 
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the 
%               first time.
%
% Part 3: Implement regularization with the cost function and gradients.
%
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%
y_n = zeros(num_labels, m);
i = 1;
for num = y'
    temp = zeros(num_labels, 1);
    temp(num,:) = 1;
    y_n(:, i) = temp;
    i = i + 1;
end

%{
disp('y:');
disp(size(y));
disp('y_n:');
disp(size(y_n));
disp('X:');
disp(size(X));
disp('Theta1:');
disp(size(Theta1));
disp('Theta2:');
disp(size(Theta2));
%}

% 5000x401
a1 = [ones(m, 1) X];
% 5000x25
z2 = a1*Theta1';
% 5000x26
a2 = [ones(m, 1) sigmoid(z2)];
% 5000x10
z3 = a2*Theta2';
% 5000x1
%[~, h] = max(z3, [], 2);
% 5000x10
h = sigmoid(z3);
J = 1/m*sum(sum(-y_n'.*log(h) - (1-y_n)'.*log(1 - h)));

Theta1Reg = Theta1;
Theta1Reg(:, 1) = [];
Theta2Reg = Theta2;
Theta2Reg(:, 1) = [];
reg = lambda/2/m*(sum(sum(Theta1Reg.^2)) + sum(sum(Theta2Reg.^2)));

J = J + reg;

for t = 1:m
    % Letting x = a and y = z
    % 1x401
    x1 = a1(t, :);
    % 1x25
    y2 = z2(t, :);
    % 1x26
    x2 = a2(t, :);
    % 1x10
    y3 = z3(t, :);
    % 1x10
    x3 = h(t, :);
    % 10x1
    delta3 = (x3' - y_n(:, t));
    % 26x1
    delta2 = Theta2'*delta3.*sigmoidGradient([1; y2']);
    % 25x1
    delta2 = delta2(2:end);
    Theta1_grad = Theta1_grad + delta2*x1;
    Theta2_grad = Theta2_grad + delta3*x2;
end
Theta1_grad = 1/m*Theta1_grad;
Theta2_grad = 1/m*Theta2_grad;

Theta1_grad_reg = lambda/m*Theta1;
Theta1_grad_reg(:, 1) = zeros(size(Theta1, 1), 1);
Theta2_grad_reg = lambda/m*Theta2;
Theta2_grad_reg(:, 1) = zeros(size(Theta2, 1), 1);

Theta1_grad = Theta1_grad + Theta1_grad_reg;
Theta2_grad = Theta2_grad + Theta2_grad_reg;










% -------------------------------------------------------------

% =========================================================================

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];


end
