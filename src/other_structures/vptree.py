from collections import namedtuple
from collections import deque
import random
import numpy as np
import heapq
import gmpy
import json
import pickle as pickle
import time

# class NDPoint(object):
#     """
#     A point in n-dimensional space
#     """

#     def __init__(self, x, idx=None):
#         self.x = np.array(x)
#         self.idx = idx
#     def __repr__(self):
#         return "NDPoint(idx=%s, x=%s)" % (self.idx, self.x)

class VPTree(object):
    """
    An efficient data structure to perform nearest-neighbor
    search. 
    """

    def __init__(self, points, dist_fn=None):
        self.left = None
        self.right = None
        self.mu = None
        self.dist_fn = dist_fn if dist_fn is not None else self.compareHashes

        # choose a better vantage point selection process
        self.vp = points.pop(random.randrange(len(points)))

        if len(points) < 1:
            return

        # choose division boundary at median of distances
        distances = [self.dist_fn(self.vp, p) for p in points]
        self.mu = np.median(distances)

        left_points = []  # all points inside mu radius
        right_points = []  # all points outside mu radius
        for i, p in enumerate(points):
            d = distances[i]
            if d >= self.mu:
                right_points.append(p)
            else:
                left_points.append(p)

        if len(left_points) > 0:
            self.left = VPTree(points=left_points, dist_fn=self.dist_fn)

        if len(right_points) > 0:
            self.right = VPTree(points=right_points, dist_fn=self.dist_fn)

    def is_leaf(self):
        return (self.left is None) and (self.right is None)

    def compareHashes(self, hash1, hash2):
        hash1 = hash1[1]
        hash2 = hash2[1]
        difference = hash1 ^ hash2
        return gmpy.popcount(difference)

class PriorityQueue(object):
    def __init__(self, size=None):
        self.queue = []
        self.size = size

    def push(self, priority, item):
        self.queue.append((priority, item))
        self.queue.sort()
        if self.size is not None and len(self.queue) > self.size:
            self.queue.pop()


### Distance functions
# def l2(p1, p2):
#     return np.sqrt(np.sum(np.power(p2.x - p1.x, 2)))




### Operations
def get_nearest_neighbors(tree, q, k=1):
    """
    find k nearest neighbor(s) of q
    :param tree:  vp-tree
    :param q: a query point
    :param k: number of nearest neighbors
    """

    # buffer for nearest neightbors
    neighbors = PriorityQueue(k)

    # list of nodes ot visit
    visit_stack = deque([tree])

    # distance of n-nearest neighbors so far
    tau = np.inf

    while len(visit_stack) > 0:
        node = visit_stack.popleft()
        if node is None:
            continue

        d = tree.dist_fn(q, node.vp)
        if d < tau:
            neighbors.push(d, node.vp)
            tau, _ = neighbors.queue[-1]

        if node.is_leaf():
            continue

        if d < node.mu:
            if d < node.mu + tau:
                visit_stack.append(node.left)
            if d >= node.mu - tau:
                visit_stack.append(node.right)
        else:
            if d >= node.mu - tau:
                visit_stack.append(node.right)
            if d < node.mu + tau:
                visit_stack.append(node.left)
    return neighbors.queue


def get_all_in_range(tree, q, tau):
    """
    find all points within a given radius of point q
    :param tree: vp-tree
    :param q: a query point
    :param tau: the maximum distance from point q
    """

    # buffer for nearest neightbors
    neighbors = []

    # list of nodes to visit
    visit_stack = deque([tree])

    while len(visit_stack) > 0:
        node = visit_stack.popleft()
        if node is None:
            continue

        d = tree.dist_fn(q, node.vp)
        if d < tau:
            neighbors.append((d, node.vp))

        if node.is_leaf():
            continue

        if d < node.mu:
            if d < node.mu + tau:
                visit_stack.append(node.left)
            if d >= node.mu - tau:
                visit_stack.append(node.right)
        else:
            if d >= node.mu - tau:
                visit_stack.append(node.right)
            if d < node.mu + tau:
                visit_stack.append(node.left)
    return neighbors

def jdefault(o):
    return o.__dict__

class MyEncoder(json.JSONEncoder):
    def default(self, o):
        return o.__dict__

if __name__ == '__main__':
    # X = np.random.uniform(0, 100000, size=10000)
    # Y = np.random.uniform(0, 100000, size=10000)
    # points = [NDPoint(x,i) for i, x in  enumerate(zip(X,Y))]
    
    print 'loading hashes'
    with open('hashes2.json') as hashFile:  
        cardHashes = json.load(hashFile)
    cardHashes = cardHashes.items()
    print 'creating tree'
    tree = VPTree(cardHashes)

    # print 'loading tree'
    start = time.time()
    # tree = pickle.load(open('savedVPTree.p', 'rb'))
    # print 'tree loaded'
    q = ('testName', 15089378856224868690)
    # neighbors = get_nearest_neighbors(tree, q, 5)
    neighbors = get_all_in_range(tree, q, 13)
    midtime = time.time()
    print 'loadtime', midtime - start
    print "query:"
    print "\t", q
    print "nearest neighbors: "
    for d, n in neighbors:
        print "\t", n
    q = ('testName', 500)
    print "query:"
    print "\t", q
    print "nearest neighbors: "
    for d, n in neighbors:
        print "\t", n
    q = ('testName', 900)
    print "query:"
    print "\t", q
    print "nearest neighbors: "
    for d, n in neighbors:
        print "\t", n
    q = ('testName', 345)
    print "query:"
    print "\t", q
    print "nearest neighbors: "
    for d, n in neighbors:
        print "\t", n
    end = time.time()
    print 'tree lookup time:', end - midtime
    print 'total runtime:', end - start
    pickle.dump(tree, open('savedVPTree.p', 'wb'), -1)
    # with open('savedVPTree.json', 'w') as outfile:
    #     json.dumps(tree.__dict__, outfile)
