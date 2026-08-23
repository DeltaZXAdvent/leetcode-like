-- | <https://codeforces.com/contest/2119/problem/B>
-- 
-- Data.Bits.bitSize (0 :: Int) >= 32
-- 
-- \( \max \{0,2\max a_i-\sum a_i \} \le d \le \sum a_i \)
main = do t <- readLn
          foldl (>>) (return ()) (replicate t testCase)
testCase = do n <- readLn :: IO Int
              line <- getLine
              let px, py, qx, qy :: Int
                  [px, py, qx, qy] = map read (words line)
              line <- getLine
              let a :: [Int]
                  a = map read (words line)
              let d :: Double
                  d = sqrt $ fromIntegral ((px - qx) ^ 2 + (py - qy) ^ 2)
              putStrLn (if solve d a then "Yes" else "No")
solve d a = 2 * max - s <= d && d <= s
  where max = fromIntegral (maximum a)
        s = fromIntegral (sum a)
