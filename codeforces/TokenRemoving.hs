-- | <https://codeforces.com/contest/2119/problem/D>
-- 
-- assert (Data.Bits.bitSize (0 :: Int) >= 32)
--
-- TODO Complex combinatorics
main = do t <- readLn
          foldl (>>) (return ()) (replicate t testCase)
testCase = do line <- getLine
              let n, m :: Int
                  [n, m] = map read (words line)
              print (solve n m)
solve n m = 
