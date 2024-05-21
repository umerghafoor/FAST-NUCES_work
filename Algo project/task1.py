def count_valid_structures(num_blocks):
    dp_array = [0] * (num_blocks + 1)
    dp_array[0] = 1

    for i in range(1, num_blocks + 1):
        for j in range(num_blocks, i - 1, -1):
            dp_array[j] += dp_array[j - i]
            
    return (dp_array[num_blocks] - 1)

# taking input form the user
print("Enter the number of blocks: ")
num_blocks = int(input())
print('Total Number of Combinations:',count_valid_structures(num_blocks))
