"""
for string 678
p 3
d 2
"""
d = 10
p = 7

def deadRMod():
   h1 = (5 * d + 6) % p
   print(h1)
   h2 = (6 * d + 7) % p
   print(h2)
   print(6 * d)
   print((h1 - 5 * d % p) * d)
   fucking_blind = ((h1 - 5 * d % p) * d + 7) % p
   print(fucking_blind)
   if fucking_blind == h2:
      print("make sense")
   else:
      print("silly")


deadRMod()
