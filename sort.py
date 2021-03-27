def mergeSort(arr):
    if len(arr[1]) > 1:
        mid = len(arr[1]) // 2

        L = arr[1][:mid]
        R = arr[1][mid:]
        
        mergeSort(L)
        mergeSort(R)

        i=j=k=0

        while i<len(L) and j<len(R):
            if L[i] < R[j]
