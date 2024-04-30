import struct
import numpy as np
from tqdm import tqdm




VECTOR_DIMENSION = 102
QUERY_DIMENSION = 104
K = 100


def read_data(data_path: str) -> np.ndarray:
    try:
    # Open the binary file for reading
        with open(data_path, "rb") as file:
            
            # Read the number of vectors
            num_vectors_bytes = file.read(4)  # Assuming uint32_t is 4 bytes
            NUM_VECTORS = struct.unpack('<I', num_vectors_bytes)[0]
            
            # Create a numpy array to store the vectors
            vectors = np.zeros((NUM_VECTORS, VECTOR_DIMENSION), dtype=np.float32)

            # Read each vector
            for _ in tqdm(range(NUM_VECTORS)):
                vectors[_] = read_bytes(file, VECTOR_DIMENSION)   
    except IOError:
        print("Error opening or reading data file")
    return vectors
       

def read_query(query_path: str) -> np.ndarray:
    try:
    # Open the binary file for reading
        with open(query_path, "rb") as file:

            # Read the number of queries
            num_queries_bytes = file.read(4)  # Assuming uint32_t is 4 bytes
            NUM_QUERIES = struct.unpack('<I', num_queries_bytes)[0]

            # Create a numpy array to store the vectors
            queries = np.zeros((NUM_QUERIES, QUERY_DIMENSION),dtype=np.float32)

            # Read each query
            for _ in tqdm(range(NUM_QUERIES)):
                queries[_] = read_bytes(file, QUERY_DIMENSION)
                
    except IOError:
        print("Error opening or reading query file")
    return queries


def read_bytes(file, num_bytes):
    return  np.frombuffer(file.read(num_bytes * 4), dtype=np.float32)
  
  
  