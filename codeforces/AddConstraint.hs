-- | <https://codeforces.com/contest/2119/problem/E>
-- 
-- assert (Data.Bits.bitSize (0 :: Int) >= 32)
--
-- TODO seems a good problem involving bounded integer techniques?
main = do t <- readLn
          foldl (>>) (return ()) (replicate t testCase)
testCase = do line <- getLine
              let a :: [Int]
                  a = map read (words line)
              print (solve )
solve a = 
