-- | <https://codeforces.com/contest/2119/problem/C>
-- 
-- Data.Bits.bitSize (0 :: Int) >= 32
import Data.Int (Int64)
import Data.Bits ((.&.), complement)
main = do t <- readLn
          foldl (>>) (return ()) (replicate t testCase)
testCase = do line <- getLine
              let n, l, r, k :: Int64
                  [n, l, r, k] = map read (words line)
              print (solve n l r k)
solve n l r k = if even n
                then if (complement l) .&. r <= l -- r has a higher highest bit
                     then -1
                     else if n == 2
                          then if l == 0
                               then 0
                               else -1
                          else if k <= n - 2
                               then l
                               else smallestPowerOfTwoGreaterThan l
                else l -- \(a_i=l\)
smallestPowerOfTwoGreaterThan :: Int64 -> Int64
smallestPowerOfTwoGreaterThan n =
  try 1
  where try m = if m > n
                then m
                else try (m * 2)
