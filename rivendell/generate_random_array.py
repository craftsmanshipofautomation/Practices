import random 
  

def Rand(start, end, num): 
    res = [] 
  
    for j in range(num): 
        res.append(random.randint(start, end)) 
  
    return res 
  
num = 100
start = 0
end = 1000
list_ = Rand(start, end, num)
list_.sort()


list2 = range(1000)
def print2(lst, size, column):
   start = 0
   end = column
   print("{")
   while 1:
      for i in lst[start:end]:
         print(i, end=", ")
      print()
      start += column
      end += column
      if start < size and end > size:
         end = size
      if start > size:
         break
   print("}")   

print2(list2, 1000, 15) 