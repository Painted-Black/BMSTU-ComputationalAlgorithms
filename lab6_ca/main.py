from math import e

a0 = 1
a1 = 2
a2 = 3

x_start = 1
x_step = 1
x_amount = 10

# def f(x):
#     return e**x

def f(x):
    return a0 * x / (a1 + a2 * x)

def create_table(start, step, q):
    x_tbl = [start + step * i for i in range(q)]
    y_tbl = [f(x) for x in x_tbl]
    return x_tbl, y_tbl

def left_difference(y, h):
    ld = [None]
    for i in range(1, len(y)):
        ld.append((y[i] - y[i-1]) / h)
    return ld

def central_difference(y, h):
    cd = [None]
    for i in range(1, len(y)-1):
        cd.append((y[i+1] - y[i-1]) / (2 * h))
    cd.append(None)
    return cd

def edges(y, h):
    l = len(y)
    ed = [None for y in range(l)]
    ed[0] = (-3 * y[0] + 4 * y[1] - y[2]) / (2 * h)
    ed[l - 1] = (y[l - 3] - 4 * y[l - 2] + 3 * y[l - 1]) / (2 * h)
    return ed

def runge_left(y, h):
    n = len(y)
    p = 1
    q = 2
    yh = left_difference(y, h)
    y2h = [0 if i < 2 else (y[i] - y[i-2]) / (2*h) for i in range(0, n)]

    res = [None, None]
    for i in range(2, n):
        res.append(yh[i] + (yh[i] - y2h[i]) / (q ** p - 1))
    return res

def leveling_variables(x, y):
    # n = 1 / y
    # з = 1 / x
    n = len(x)
    res = [0] * n
    for i in range(n):
        if x[i] != 0:
            res[i] = (a1 * (y[i] ** 2)) / ((x[i] ** 2) / a0)
        else:
            res[i] = None
    return res

def new_align(x, y):
    # n = x / y
    # з = x
    n = len(x)
    res = [0] * n

    for i in range(n):
        if x[i] != 0:
             res[i] = (a2 / a0) * (y[i] ** 2 / x[i]) * \
                      (((a1 + a2 * x[i]) ** 2) / (a0 * (a1 + a2 * x[i]) - a2 * a0 * x[i]))
        else:
            res[i] = None

    return res

def derivative(x):
    return (a0 * (a1 + a2 * x) - a2 * a0 * x) / ((a1 + a2 * x) ** 2)

def accurate_derivative(x):
    ad = []
    for i in range(len(x)):
        ad.append(derivative(x[i]))
    return ad

def print_line(name, table):
    print("{:<20}".format(name), end="")
    for i in table:
        if (i != None):
            print("{: <15.4f}".format(i), end="")
        else:
            print("{: <15}".format("None"), end="")
    print()

x_table, y_table = create_table(x_start, x_step, x_amount)
left_diff = left_difference(y_table, x_step)
central_diff = central_difference(y_table, x_step)
edg = edges(y_table, x_step)
rng = runge_left(y_table, x_step)
align = leveling_variables(x_table, y_table)
ad = accurate_derivative(x_table)
na = new_align(x_table, y_table)


str_ld = []
str_cd = []
str_edg = []
str_rng = []
str_al = []
for i in range(len(x_table)):
    if left_diff[i] == None:
        str_ld.append("None" + " " * (20 - len("None")))
    else:
        str_ld.append("{: <15.4f}".format(left_diff[i]))

    if central_diff[i] == None:
        str_cd.append("None" + " " * (20 - len("None")))
    else:
        str_cd.append("{: <15.4f}".format(central_diff[i]))

    if edg[i] == None:
        str_edg.append("None" + " " * (20 - len("None")))
    else:
        str_edg.append("{: <15.4f}".format(edg[i]))

    if rng[i] == None:
        str_rng.append("None" + " " * (20 - len("None")))
    else:
        str_rng.append("{: <15.4f}".format(rng[i]))


print("x " + " " * (20 - len("x")),
      "y " + " " * (20 - len("y")),
      "left diff " + " " * (20 - len("left diff")),
      "central diff " + " " * (20 - len("central diff")),
      "edges " + " " * (20 - len("edges")),
      "Runge " + " " * (20 - len("Runge")),
      "align" + " " * (20 - len("Runge")),
      "accurate" + " " * (20 - len("Runge")),
      "new_align")

for i in range(len(x_table)):
    print("{: <15.4f}".format(x_table[i]), " " * (20 - len("{: <15.4f}".format(x_table[i]))),
          "{: <15.4f}".format(y_table[i]), " " * (20 - len("{: <15.4f}".format(y_table[i]))),
          str_ld[i], " " * (20 - len(str_ld[i])),
          str_cd[i], " " * (20 - len(str_cd[i])),
          str_edg[i], " " * (20 - len(str_edg[i])),
          str_rng[i], " " * (20 - len(str_rng[i])),
          "{: <15.4f}".format(align[i]), " " * (20 - len("{: <15.4f}".format(align[i]))),
          "{: <15.4f}".format(ad[i]), " " * (20 - len("{: <15.4f}".format(ad[i]))),
          "{: <15.4f}".format(na[i]))





