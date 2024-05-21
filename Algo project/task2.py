def calc_optimal_position(strategic_values, num_attacks):
    size = len(strategic_values)
    num_attacks = num_attacks 
    # Initialize a 2D array to store intermediate results
    dp = [[float('inf')] * (num_attacks + 2) for _ in range(size + 1)]
    dp[0][0] = 0

    for i in range(1, size + 1): # run N times
        for k in range(i): #run N times
            for j in range(1, min(i, num_attacks + 1) + 1):# run M times
                if(dp[k][j - 1]>=float('inf')):
                    continue
                # Calculate cost of current attack
                local_cost = 0
                for m in range(k, i):
                    for n in range(m + 1, i):
                        local_cost += strategic_values[m] * strategic_values[n]
                # Update dp array with minimum cost
                dp[i][j] = min(dp[i][j], dp[k][j - 1] + local_cost)

    return dp[size][num_attacks + 1]

print("Enter the number of blocks and number of attacks: ")
num_blocks, num_attacks = map(int, input().split())
print("Enter the strategic values: ")
strategic_values = list(map(int, input().split()))
zeros = list(map(int, input().split()))
print('Minimum Cost:',calc_optimal_position(strategic_values, num_attacks))