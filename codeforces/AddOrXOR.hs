-- <https://codeforces.com/contest/2119/problem/A>
-- Data.Bits.bitSize (0 :: Int) >= 32
import Data.Bits (xor)
main = do t <- readLn :: IO Int
          foldl (>>) (return ()) (replicate t testCase)
testCase = do line <- getLine
              let a, b, x, y :: Int
                  [a, b, x, y] = map read (words line)
              print (solve a b x y)
solve :: Int -> Int -> Int -> Int -> Int
solve a b x y = case compare a b of
  LT | x > y,
       let adds = div b 2 - div a 2
           xors = (b - a) - adds
       -> adds * x + xors * y
     | otherwise -> (b - a) * x
  EQ -> 0
  GT | xor a 1 == b -> y
     | otherwise -> -1
