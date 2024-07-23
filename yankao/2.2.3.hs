module Main where
-- Haskell data structures are probably not corresponding to physical ones.
-- But let's do it.
import Data.List
import Data.Maybe
deleteMinimum :: Ord a => [a] -> [a]
deleteMinimum l = concat [fst ls, last (snd ls) : (init (drop 1 (snd ls)))]
  where ls = splitAt (fromJust (elemIndex (minimum l) l)) l
main_print l = do
  print (l)
  print (deleteMinimum l)
main = main_print [412,454,784,454]
