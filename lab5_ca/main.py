from math import exp, log


def get_data(file_name):
    file = open(file_name, 'r')
    x = []
    for str in file:
        str = str[:-1]
        a = str.split(' ')
        b = []
        for i in range(len(a)):
            b.append(float(a[i]))
        x.append(b)
    return x


def quicksort(arr):
    if len(arr) <= 1:
        return arr
    else:
        q = arr[(int)(len(arr) / 2)]
        l_arr = [n for n in arr if n < q]
        e_arr = [q] * arr.count(q)
        b_arr = [n for n in arr if n > q]
        return quicksort(l_arr) + e_arr + quicksort(b_arr)


def bin_search(arr, item, first, last):
    if first == last:
        return first
    else:
        i = int((first + last) / 2)
        if arr[i] > item:
            return bin_search(arr, item, first, i)
        else:
            return bin_search(arr, item, i + 1, last)


def get_nodes(x_data, nearest, x_0, n):
    mas = [0] * (n + 1)
    count = 1
    mas[0] = nearest
    last = x_data[nearest]
    last_ind = nearest
    while (count < n + 1):
        if (last > x_0):
            if (last_ind - count >= 0):
                mas[count] = last_ind - count
                last_ind -= count
            else:
                mas[count] = last_ind + 1
                last_ind += 1
        else:
            if (last_ind + count < len(x_data)):
                mas[count] = last_ind + count
                last_ind += count
            else:
                mas[count] = last_ind - 1
                last_ind -= 1
        last = x_data[last_ind]
        count += 1

    mas = quicksort(mas)
    return mas


def get_dif(prev, x, number):
    mas = [0] * (len(prev) - 1)
    for i in range(len(mas)):
        mas[i] = (prev[i + 1] - prev[i]) / (x[i + number] - x[i])
    return mas


def interpol(x_data, y_data, x_0, n):
    x = [0] * (n + 1)
    y = [0] * (n + 1)
    y_dif = []
    for i in range(n + 1):
        y_dif.append([])

    nearest = bin_search(x_data, x_0, 0, len(x_data) - 1)

    ind = [0] * (n + 1)
    ind = get_nodes(x_data, nearest, x_0, n)
    for i in range(len(ind)):
        x[i] = x_data[ind[i]]
        y[i] = y_data[ind[i]]

    y_dif[0] = y
    for i in range(1, n + 1):
        y_dif[i] = get_dif(y_dif[i - 1], x, i)
    p = y[0]
    px = 1
    for i in range(1, n + 1):
        px *= (x_0 - x[i - 1])
        p += y_dif[i][0] * px
    return p


def get_Q(ind, T):
    data = get_data('file5.txt')
    razmer = len(data)

    temperatura = [0] * razmer
    stat_sum = [0] * 6
    for i in range(6):
        stat_sum[i] = [0] * razmer

    for i in range(razmer):
        temperatura[i] = data[i][0]
        stat_sum[1][i] = data[i][1]
        stat_sum[2][i] = data[i][2]
        stat_sum[3][i] = data[i][3]
        stat_sum[4][i] = data[i][4]
        stat_sum[5][i] = data[i][5]

    if (T in temperatura):
        Q = stat_sum[ind][temperatura.index(T)]
    else:
        Q = interpol(temperatura, stat_sum[ind], T, 4)
    return Q


def get_dE(i, T, Gamma, Z):
    ind = (int)(i)
    ind1 = ind + 1
    return 8.61 * (10 ** (-5)) * T * log(
        (1 + (Z[ind1] ** 2) * Gamma / 2) * (1 + Gamma / 2) / (1 + (Z[ind] ** 2) * Gamma / 2))


def get_K(i, T, Gamma, Z):
    E = [0, 12.13, 20.98, 31.0, 45.0]
    Qi = get_Q(i, T)
    Qi1 = get_Q(i + 1, T)
    return 4.83 * (10 ** -3) * (Qi1 / Qi) * (T ** (3 / 2)) * exp(-(E[i] - get_dE(Gamma, T, i, Z)) * 11603 / T)


def get_Alpha(Gamma, T):
    return 0.285 * (10 ** (-11)) * ((Gamma * T) ** 3)


def func_for_Gamma(T, X, Z, a):
    res = 0
    for i in range(2, 5):
        res += (exp(X[i]) * (Z[i] ** 2)) / (1 + (Z[i] ** 2) * a / 2)

    Gamma = a ** 2 - 5.87 * (10 ** 10) * (1 / (T ** 3)) * (exp(X[0]) / (1 + (a / 2)) + res)
    return Gamma


def get_Gamma(T, X, Z):
    eps = 1e-7
    a = 0
    b = 2
    c = 1
    while (abs((b - a) / c) > eps):
        c = (a + b) / 2
        fc = func_for_Gamma(T, X, Z, c)
        fa = func_for_Gamma(T, X, Z, a)
        if (fc * fa < 0):
            b = c
        else:
            a = c
    return c


def gauss(m):
    for col in range(len(m[0])):
        for row in range(col + 1, len(m)):
            r = [(rowValue * (-(m[row][col] / m[col][col]))) for rowValue in m[col]]
            m[row] = [sum(pair) for pair in zip(m[row], r)]
    ans = []
    m.reverse()
    for sol in range(len(m)):
        if sol == 0:
            ans.append(m[sol][-1] / m[sol][-2])
        else:
            inner = 0
            for x in range(sol):
                inner += (ans[x] * m[sol][-2 - x])
            ans.append((m[sol][-1] - inner) / m[sol][-sol - 2])
    ans.reverse()
    return ans


def make_matrix(X, T, P, Z, Gamma):
    mtr = 6 * [0]
    for i in range(6):
        mtr[i] = 7 * [0]
    Alpha = get_Alpha(Gamma, T)
    mtr[0] = [1, -1, 1, 0, 0, 0, -(X[0] + X[2] - X[1] - log(get_K(1, T, Gamma, Z)))]
    mtr[1] = [1, 0, -1, 1, 0, 0, -(X[0] + X[3] - X[2] - log(get_K(2, T, Gamma, Z)))]
    mtr[2] = [1, 0, 0, -1, 1, 0, -(X[0] + X[4] - X[3] - log(get_K(3, T, Gamma, Z)))]
    mtr[3] = [1, 0, 0, 0, -1, 1, -(X[0] + X[5] - X[4] - log(get_K(4, T, Gamma, Z)))]
    mtr[4] = [exp(X[0]), 0, -Z[2] * exp(X[2]), -Z[3] * exp(X[3]),
              -Z[4] * exp(X[4]), -Z[5] * exp(X[5]),
              -(exp(X[0]) - (Z[2] * exp(X[2]) + Z[3] * exp(X[3]) + Z[4] * exp(X[4]) + Z[5] * exp(X[5])))]
    mtr[5] = [exp(X[0]), exp(X[1]), exp(X[2]), exp(X[3]), exp(X[4]), exp(X[5]),
              -(exp(X[0]) + exp(X[1]) + exp(X[2]) + exp(X[3]) + exp(X[4]) + exp(X[5]) - Alpha - P * 7243 / T)]

    return mtr


def refinement(X, T, P, Z, Gamma):
    eps = 1e-4
    mtr = make_matrix(X, T, P, Z, Gamma)
    dX = gauss(mtr)
    new_Gamma = get_Gamma(T, X, Z)

    while (max(abs(dX[0] / X[0]), abs(dX[1] / X[1]), abs(dX[2] / X[2]), abs(dX[3] / X[3]), abs(dX[4] / X[4]),
               abs(dX[5] / X[5]),
               abs((Gamma - new_Gamma) / new_Gamma))) > eps:

        for i in range(6):
            X[i] += dX[i]
        Gamma = new_Gamma
        new_Gamma = get_Gamma(T, X, Z)

        mtr = make_matrix(X, T, P, Z, Gamma)
        dX = gauss(mtr)

    return X, new_Gamma


def solve_system(T, P):
    Z = [0, 0, 1, 2, 3, 4]
    Gamma = 0
    X = [-1, 3, -1, -15, -25, -35]

    res, Gamma = refinement(X, T, P, Z, Gamma)
    res.append(Gamma)
    return res


def cur_t(z):
    return T0 + (Tw - T0) * z ** m


hn = 40


def find_nt(t, p, flag):
    # return p * 7243 / t
    res = solve_system(t, p)
    sum_Nt = 0
    for i in range(6):
        res[i] = exp(res[i])
        sum_Nt += res[i]
    if flag == 1:
        for i in range(6):
            print("n", i, ": ", res[i], sep='')
        print("Gamma:", res[6])
    return sum_Nt


def F(p, flag):
    # метод трапеции
    hz = 1 / hn
    zi = (hn + 1) * [0]
    Tz = (hn + 1) * [0]
    Nt = (hn + 1) * [0]
    f_int = (hn + 1) * [0]
    zi2 = (hn + 1) * [0]  #
    zi3 = (hn + 1) * [0]  #
    Tz2 = (hn + 1) * [0]  #
    Tz3 = (hn + 1) * [0]  #
    Nt2 = (hn + 1) * [0]  #
    Nt3 = (hn + 1) * [0]  #

    for i in range(hn):
        zi[i] = i * hz
        zi2[i] = i * hz + hz / 2
        zi3[i] = i * hz + hz
        Tz[i] = cur_t(zi[i])
        Tz2[i] = cur_t(zi2[i])
        Tz3[i] = cur_t(zi3[i])
        Nt[i] = find_nt(Tz[i], p, flag * (i + 1))
        Nt2[i] = find_nt(Tz2[i], p, 0)
        Nt3[i] = find_nt(Tz3[i], p, 0)
        f_int[i] = Nt[i] * zi[i] + 4 * Nt2[i] * zi2[i] + Nt3[i] * zi3[i]

    integral = 0
    for i in range(hn):
        integral += f_int[i]
    integral *= hz / 6
    # print(integral)

    # for i in range(hn + 1):
    #     zi[i] = i * hz
    #     Tz[i] = cur_t(zi[i])
    #     Nt[i] = find_nt(Tz[i], p, flag * (i + 1))
    #     f_int[i] = Nt[i] * zi[i]
    #
    # integral = (f_int[0] + f_int[hn]) / 2
    # for i in range(1, hn):
    #     integral += f_int[i]
    # integral *= hz
    #
    # print(integral)

    res = koef - 2 * integral
    return res


T0 = int(input('Введите T0: '))
Tw = int(input('Введите Tw: '))
m = int(input("Введите m: "))
Pnm = 0.5  # начальное давление, атм
Tnm = 300  # Начатальная температура, К

koef = Pnm / Tnm * 7243  # концентрация

a = 2
b = 25
p = a
eps = 1e-4

f0 = F(a, 0)

# данный метод описывает алгоритм нахождение корней (нулей) функции
while abs((a - b) / p > eps):
    p = (a + b) / 2
    if f0 * F(p, 0) < 0:
        b = p
    else:
        a = p
print("Ответ:  ", round((a + b) / 2, 7))

F((a + b) / 2, 1)



