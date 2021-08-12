#heapify function
def heapify(arr, n, i):
    largest = i  # Initialize largest as root
    l = 2 * i + 1     # left = 2*i + 1
    r = 2 * i + 2     # right = 2*i + 2
  
    # See if left child of root exists and if greater than root
    if l < n and arr[1][i] < arr[1][l]:
        largest = l
  
    # See if right child of root exists and if greater than root
    if r < n and arr[1][largest] < arr[1][r]:
        largest = r
  
    # Change root, if needed
    if largest != i:
        arr[1][i],arr[1][largest] = arr[1][largest],arr[1][i]  # swap output values
        arr[0][i],arr[0][largest] = arr[0][largest],arr[0][i]  # swap input values
        # Heapify the root.
        heapify(arr, n, largest)
  
#heapsort function
def heapSort(arr):
    n = len(arr[1])
  
    # Build a maxheap.
    # Since last parent will be at ((n//2)-1) we can start at that location.
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
  
    # One by one extract elements
    for i in range(n-1, 0, -1):
        arr[1][i], arr[1][0] = arr[1][0], arr[1][i]   # swap output values
        arr[0][i], arr[0][0] = arr[0][0], arr[0][i]   # swap input values
        heapify(arr, i, 0)
