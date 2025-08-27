###
# Python code to generate a set of matrice, along with there corresponding inverse
# For the purpose of testing the Matrix2.Inverse methos.
#

# Import the library we need.
# numpy provide the functionality we need to invert matrices.
import numpy as np

# Define the dimension of the matrices se are create.
# Note the the number of rows and colums have to be the same as these
# have to be square matrices.
numRows = 5
numCols = numRows

# Define how many matrices to generate.
numMatrices = 10000

# Loop and generate the matrices    
for i in range (0, numMatrices):
    
    # Generate the matrix
    A = (np.random.randint(20, size=(numRows, numCols))) - 10
    
    # Compute the inverse
    AInv = np.linalg.inv(A)
    
    # Concatenate these togheter.
    if (i<1):
        B = np.concatenate((A, AInv), axis=1)
    else:
        B = np.concatenate((B, np.concatenate((A, AInv), axis=1)), axis=0)
        

# Save all of matrices into a single .csv file
np.savetxt("test.csv", B, delimiter=",", header=str(numRows))
