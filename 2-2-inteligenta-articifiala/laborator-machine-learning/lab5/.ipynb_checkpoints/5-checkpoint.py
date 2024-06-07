import numpy as np
from sklearn.linear_model import LinearRegression, Ridge, Lasso
from sklearn.metrics import mean_squared_error, mean_absolute_error
from sklearn.utils import shuffle

#
# # definirea modelelor
# linear_regression_model = LinearRegression()
# ridge_regression_model = Ridge(alpha=1)
# lasso_regression_model = Lasso(alpha=1)
# # calcularea valorii MSE și MAE
# mse_value = mean_squared_error(y_true, y_pred)
# mae_value = mean_absolute_error(y_true, y_pred)


training_data = np.load('data/training_data.npy')
prices = np.load('data/prices.npy')
# print('The first 4 samples are:\n ', training_data[:4])
# print('The first 4 prices are:\n ', prices[:4])
# shuffle
training_data, prices = shuffle(training_data, prices, random_state=0)


def normalize(training_data):
    training_norm = (training_data - np.mean(training_data, axis=0)) / (np.std(training_data, axis=0) + 0.0000000000001)

    return training_norm


def ex2(training_data, prices):
    training_data = normalize(training_data)
    linear_regression_model = LinearRegression()

    size = int(0.8 * np.size(training_data, axis=0))
    print(size)
    train, train_prices = training_data[:size], prices[:size]
    test, test_prices = training_data[size + 1:], prices[size + 1:]


    linear_regression_model.fit(train, train_prices)
    pred = linear_regression_model.predict(test)
    print(mean_squared_error(test_prices, pred))
    print(mean_absolute_error(test_prices, pred))


ex2(training_data, prices)
