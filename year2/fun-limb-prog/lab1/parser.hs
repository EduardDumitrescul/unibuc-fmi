import Data.Char
import Text.XHtml (base)

newtype Parser a = Parser { parse :: String -> [(a,String)] }

item :: Parser Char
item = Parser (\cs -> case cs of
                "" -> []
                (c:cs) -> [(c,cs)])

instance Monad Parser where
    return a = Parser (\cs -> [(a,cs)])
    p >>= f = Parser (\cs -> concat (map (\(a, cs') -> (parse (f a) cs')) (parse p cs)))

instance Applicative Parser where
    pure = return
    mf <*> ma = do
        f <- mf
        va <- ma
        return (f va)    

instance Functor Parser where              
    fmap f ma = pure f <*> ma   
  
{-
instance Functor Parser where              
    fmap g p = Parser (\cs -> map (\(a,cs') -> (g a, cs')) (parse p cs))

instance Applicative Parser where
    pure a = Parser (\cs -> [(a, cs)])
    pg <*> pa = Parser (\cs -> concat (map (\(g, cs') -> (parse (fmap g pa) cs')) (parse pg cs)))

instance Monad Parser where
    p >>= f = Parser (\cs -> concat (map (\(a, cs') -> (parse (f a) cs')) (parse p cs)))
-}

zero :: Parser a
zero = Parser (const [])

psum :: Parser a -> Parser a -> Parser a
psum p q = Parser (\cs -> (parse p cs) ++ (parse q cs))

(<|>) :: Parser a -> Parser a -> Parser a
p <|> q = Parser (\cs -> case parse (psum p q) cs of
                                [] -> []
                                (x:xs) -> [x])

dpsum0 :: Parser [a] -> Parser [a]
dpsum0 p = p <|> (return [])

sat :: (Char -> Bool) -> Parser Char
sat p = do
            c <- item
            if p c then return c else zero

char :: Char -> Parser Char
char c = sat (c ==)

string :: String -> Parser String
string [] = return []
string (c:cs) = do
                    pc <- char c
                    prest <- string cs
                    return (pc : prest)

many0 :: Parser a -> Parser [a]
many0 p = dpsum0 (many1 p)

many1 :: Parser a -> Parser [a]
many1 p = do 
    a <- p
    aa <- many0 p
    return (a : aa)

spaces :: Parser String
spaces = many0 (sat isSpace)

token :: Parser a -> Parser a
token p = do
            spaces
            x <- p
            spaces
            return x

symbol :: String -> Parser String
symbol symb = token (string symb)

sepBy0 :: Parser a1 -> Parser a2 -> Parser [a1]
p `sepBy0` sep = dpsum0 (p `sepBy1` sep)

sepBy1 :: Parser a1 -> Parser a2 -> Parser [a1]
p `sepBy1` sep = do
                    a <- p
                    as <- many0 (do
                                    sep
                                    p)
                    return (a:as)

look :: Parser (Maybe Char)
look = Parser (\cs -> case cs of
      [] -> [(Nothing, [])]
      (c:cs') -> [(Just c, c:cs')]
    )

takeUntil :: Char -> Parser [Char]
takeUntil stop = consumeRest "" stop
    where consumeRest acc stop = do
                                    l <- look
                                    if l == Just stop then return [] else do
                                                                            c <- item
                                                                            cs <- consumeRest (acc ++ [c]) stop
                                                                            return (c:cs)

chainl1 :: Parser t -> Parser (t -> t -> t) -> Parser t
p `chainl1` op = do
                    x <- p
                    rest x
                 where rest x = (do
                                    f <- op
                                    y <- p
                                    rest (f x y)
                                ) <|> return x

digit :: Parser Int
digit = do
            d <- sat isDigit
            return (digitToInt d)

integer :: Parser Int
integer = do
              spaces
              d <- digitToInt <$> sat isDigit
              if d == 0 
                then 
                  return 0 
                else 
                  do
                    ds <- many0 digit
                    return (asInt (d:ds))
          where asInt ds = sum [d * (10^p) | (d, p) <- zip (reverse ds) [0..] ]


integerExpr :: Parser Expr
integerExpr = do 
                rez <- integer
                return (ENum (fromIntegral rez))

number :: Parser Double
number = withDecimalPt <|> withoutDecimalPt
  where
    withoutDecimalPt = fromIntegral <$> integer
    withDecimalPt = do
                      wholePart <- withoutDecimalPt
                      char '.'
                      fractionalPart <- fmap asFracPt (many0 digit)
                      return (wholePart + fractionalPart)
    asFracPt ds = sum [fromIntegral d * (10 ** (-p)) | (d, p) <- zip ds [1..]]

numberExpr :: Parser Expr
numberExpr = do 
  res <- number
  return (ENum res)

addop :: Parser (Double -> Double -> Double)
addop = add <|> sub
  where add = do
                symbol "+"
                return (+)
        sub = do
                symbol "-"
                return (-)






addOpExpr :: Parser (Expr -> Expr -> Expr)
addOpExpr = add <|> sub
  where add = do
                symbol "+"
                return concatAdd
        concatAdd a b = EAdd a b
        sub = do
                symbol "-"
                return concatSub
        concatSub a b = ESub a b


mulop :: Parser (Double -> Double -> Double)
mulop = mul <|> div
  where mul = do
                symbol "*"
                return (*)
        div = do
                symbol "/"
                return (/)
mulOpExpr :: Parser (Expr -> Expr -> Expr)
mulOpExpr = mul <|> div
  where mul = do
                symbol "*"
                return concatMul
        concatMul a b = EMul a b
        div = do
                symbol "/"
                return concatDiv
        concatDiv a b = EDiv a b

factor :: Parser Double
factor = negativeFactor <|> parensExpr <|> number
  where
    negativeFactor = do
                        symbol "-"
                        negate <$> factor
    parensExpr = do
                    symbol "("
                    x <- expr
                    symbol ")"
                    return x

factorExpr :: Parser Expr
factorExpr = negativeFactor <|> parensExpr <|> numberExpr
  where
    negativeFactor = do
                        symbol "-"
                        ENeg <$> factorExpr
    parensExpr = do
                    symbol "("
                    x <- exprExpr
                    symbol ")"
                    return x
                    
term :: Parser Double
term = factor `chainl1` mulop

expr :: Parser Double
expr = term `chainl1` addop

termExpr :: Parser Expr
termExpr = factorExpr `chainl1` mulOpExpr

exprExpr :: Parser Expr
exprExpr = termExpr `chainl1` addOpExpr

--1. TestaČi parser-ul de mai sus

--2. CreaČi un tip de date abstract pt expresii aritmetice Či modificaČi parser-ul astfel ĂŽncĂ˘t el sÄ returneze o asemenea expresie


data Expr = ENum Double
        | EAdd Expr Expr
        | ESub Expr Expr
        | EMul Expr Expr
        | EDiv Expr Expr
        | ENeg Expr
        deriving Eq

instance Show Expr where
        show (ENum x) = show x
        show (EAdd e1 e2) = "(" ++ show e1 ++ " + " ++ show e2 ++ ")"
        show (EMul e1 e2) = "(" ++ show e1 ++ " * " ++ show e2 ++ ")"
        show (ESub e1 e2) = "(" ++ show e1 ++ " - " ++ show e2 ++ ")"
        show (EDiv e1 e2) = "(" ++ show e1 ++ " / " ++ show e2 ++ ")"
        show (ENeg e1) = "(-" ++ show e1 ++ ")"

