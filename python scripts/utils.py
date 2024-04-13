
import struct
import numpy as np
from tqdm import tqdm
from scipy.stats import norm

VECTOR_DIMENSION = 102
QUERY_DIMENSION = 104
K = 100

def read_data(data_path):
    try:
    # Open the binary file for reading
        with open(data_path, "rb") as file:
            
            # Read the number of vectors
            num_vectors_bytes = file.read(4)  # Assuming uint32_t is 4 bytes
            NUM_VECTORS = struct.unpack('<I', num_vectors_bytes)[0]
            
            # Create a numpy array to store the vectors
            vectors = np.zeros((NUM_VECTORS, VECTOR_DIMENSION))

            # Read each vector
            for _ in range(NUM_VECTORS):
                vector_bytes = file.read(4 * VECTOR_DIMENSION)  # Assuming float is 4 bytes
                vector = struct.unpack('<' + 'f' * VECTOR_DIMENSION, vector_bytes)
                vectors[_] = vector   
    except IOError:
        print("Error opening or reading data file")
    return vectors
        
def read_query(query_path):
    try:
    # Open the binary file for reading
        with open(query_path, "rb") as file:

            # Read the number of vectors
            num_queries_bytes = file.read(4)  # Assuming uint32_t is 4 bytes
            NUM_QUERIES = struct.unpack('<I', num_queries_bytes)[0]

            # Create a numpy array to store the vectors
            queries = np.zeros((NUM_QUERIES, QUERY_DIMENSION))

            # Read each vector
            for _ in range(NUM_QUERIES):
                query_bytes = file.read(4 * QUERY_DIMENSION)  # Assuming float is 4 bytes
                query = struct.unpack('<' + 'f' * QUERY_DIMENSION, query_bytes)
                queries[_] = query
    except IOError:
        print("Error opening or reading query file")
    return queries

def read_output(output_path, NUM_QUERIES):
    
    with open(output_path, "rb") as file:
        
        vectors = np.zeros((NUM_QUERIES, K))
        
        for _ in range(NUM_QUERIES):
            vector_bytes = file.read(4 * K)  # Assuming uint32_t is 4 bytes
            vector = struct.unpack('<{}I'.format(K), vector_bytes)
            vectors[_] = vector
    return vectors
            
def knn(data, query, k):
    
    n = data.shape[0] # number of data points
    m = query.shape[0] # number of query points
    d = data.shape[1] - 2 # dimension of data points
    
    res = np.zeros((m, k), dtype=np.int32)
    dist = np.zeros((n, m), dtype=np.float32)
    dist_to_return = np.zeros((m, k), dtype=np.float32)
    
    for i in tqdm(range(m)):
        
        query_type = query[i, 0]
        query_category = query[i, 1]
        query_lower, query_higher = query[i, 2], query[i, 3]
        query_point = query[i, 4:]
        

        if query_type == 0: # normal query
            for j in range(n):
                # euclidean distance
                dist[j, i] = np.linalg.norm(data[j, 2:] - query_point)
        elif query_type == 1: # class query
            for j in range(n):
                if data[j, 0] == query_category:
                    dist[j, i] = np.linalg.norm(data[j, 2:] - query_point)
                else:
                    dist[j, i] = np.inf
        elif query_type == 2: # range query
            for j in range(n):
                if query_lower <= data[j, 1] <= query_higher:
                    dist[j, i] = np.linalg.norm(data[j, 2:] - query_point)
                else:
                    dist[j, i] = np.inf
        elif query_type == 3: # class range query
            for j in range(n):
                if query_lower <= data[j, 1] <= query_higher and data[j, 0] == query_category:
                    dist[j, i] = np.linalg.norm(data[j, 2:] - query_point)
                else:
                    dist[j, i] = np.inf
                    
        res[i] = np.argsort(dist[:, i])[:k]
        temp = dist.copy()
        dist_to_return[i] = np.sort(temp[:, i])[:k] 
        
        
    return res, dist, dist_to_return

def distances(output, dist):
    
    m = output.shape[0] # number of query points
    k = output.shape[1] # number of nearest neighbors k
    
    dist_output = np.zeros((m, k)) 
    
    for i in range(m):      
        dist_output[i] = dist[output[i], i]
    return dist_output





# Function to split the normal distribution into n equal parts 
# n:  SAX alphabet size
# and return the z-scores corresponding to the breakpoints
def split_normal_distribution(n):
    

    # Calculate cumulative probabilities for equal intervals
    cumulative_probs = np.linspace(0, 1, n + 1)

    # Find z-scores corresponding to the cumulative probabilities
    z_scores = norm.ppf(cumulative_probs)

    # Print the z-scores
    print("Breakpoints for {} equal parts:".format(n))
    for i in range(1, len(z_scores)-1):
        print("Breakpoint {}: z-score = {:.4f}".format(i, z_scores[i]))

    # Return the z-scores
    return z_scores[1:-1]