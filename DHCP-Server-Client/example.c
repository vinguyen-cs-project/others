//
//  example.c
//  
//
//  Created by Sue Nguyen on 12/5/20.
//

else if (wt[i] <= w)
    if k[i-1][w-wt[i]] != 0 && p[j] == k[i-1][w-wt[i]]
        k[i][w] = max (p[i] + k[i-1][w-wt[i]] - d[j][i], k[i][w-1], k[i-1][w])
//p[i] will give profit of current item, the big ugly k follow will return the profit of previous item needed if weight[i] < weight of our sack W, and d will be distance between prev item and current item
//instead of just taking the max of current k[i][W] and k[i-1][W], i decided we also need to compared k[i][W-1] because  at W= 5, item 1 weight = 2 and item 2 weight = 3 for example, sometimes it's smarter to just go with item 2 if the cost to deliver both 1 and 2 is too much
    else k[i][w] = max (p[i] + k[i-1][w-wt[i]], k[i-1][w])
