
def float_range(start, stop, step):
    initial_start = start
    if initial_start < stop:
        while start < stop:
            yield start
            start += step
    else:
        while start > stop:
            yield start
            start += step

def float_range_list(start, stop, step):
    res = []
    initial_start = start
    if initial_start < stop:
        while start < stop:
            res.append(start)
            start += step
    else:
        while start > stop:
            res.append(start)
            start += step
    return res
