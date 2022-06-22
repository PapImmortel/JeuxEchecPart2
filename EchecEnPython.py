from operator import truediv
import random
import chess
import tkinter as tk
from tkinter import font  as tkfont
import numpy as np
 

 


ZOOM = 40   # taille d'une case en pixels
EPAISS = 8  # epaisseur des murs bleus en pixels
board = chess.Board()
print(board)
board.push_san("e4")
print(board)
board.push_san("f5")
print(board)
board.push_san("Bc4")
print(board)
board.push_san("g6")
print(board)
board.push_san("Bg8")
print(board)
board.push_san("g5")
print(board)
board.push_san("Bb3")


print(board)

   
   
    
   
   