def saltos(i, a):
    if i >= len(a):
        return 0
    else:
        min = 1 + saltos(i+1, a)
        for j in range(2, a[i]+1):
            n =  1 + saltos(i+j, a)
            if n < min:
                min = n
        return min
    
def saltos_TD(i, a, aux):
    if i >= len(a):
        return 0
    else:
        if len(aux) == 0:
            aux = [-1 for i in range(len(a))]
        if aux[i] != -1:
            return aux[i]
        min = 1 + saltos_TD(i+1, a, aux)
        for j in range(2, a[i]+1):
            n =  1 + saltos_TD(i+j, a, aux)
            if n < min:
                min = n
        aux[i] = min
        return min

def saltos_BU(a, i):
    n = len(a)
    dp = [None for _ in range(n)]
    dp[n-1] = 0
    pos = n-2
    while pos >= 0:
        mini = 1e9
        for j in range(pos+1, pos + a[pos]+1):
            if j >= n:
                continue
            mini = min(mini, dp[j])
        dp[pos] = 1 + mini
        inde -= 1
    return dp[0]

a = [1,3,5,8,9,2,6,7,6,8,9]

print(saltos_TD(0, a, []))  # 3