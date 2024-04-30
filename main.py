from fast_ivf import FastIVF
from utils import io
import time

ndim = 100
nlist = 1024
nprobe = 10

db_type = 1

if db_type == 0:
    data_path = "dummy-data.bin"
    query_path = "dummy-queries.bin"
elif db_type == 1:
    data_path = "data/contest-data-release-1m.bin"
    query_path = "data/contest-queries-release-1m.bin"
elif db_type == 2:
    data_path = "data/contest-data-release-10m.bin"
    query_path = "data/contest-queries-release-10m.bin"




def main():
    
    #fast_ivf = FastIVF(ndim=ndim, nlist=nlist, nprobe=nprobe)

    
    start = time.time()
    data = io.read_data(data_path)
    queries = io.read_query(query_path)
    end = time.time()
    
    print("Data shape: ", data.shape)
    print("Query shape: ", queries.shape)
    print("Time taken to read data and queries: ", round((end-start) * 1000), "ms")
    
    index = FastIVF(ndim=ndim, nlist=nlist)
    
    # number of clusters to explore during search
    index.nprobe = 10
    # greedy skip voronoi cells which are having score smaller than 0.5 of the largest score
    # higher values lead to faster search but less accurate
    index.ratio_threshold = 0.5
    
    # train the index (add the data to the index)
    index.train(data[:, 2:])
   
    # search the index
    distances, indices = index.search(queries[:,4:], k=100)
    
    
    
    


if __name__ == '__main__':
    main()