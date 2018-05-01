type data = int;
type height = int;
datatype AVL = Leaf
            |  Node of AVL * data * height * AVL;

fun getH Leaf = ~1
  | getH (Node(_, _, h, _)) = h;
fun maxH(lhs:height, rhs:height) = if lhs > rhs then lhs else rhs;

fun getL Leaf = Leaf
  | getL (Node(l, _, _, _)) = l;
fun getR Leaf = Leaf
  | getR (Node(_, _, _, r)) = r;
fun getD Leaf = 0
  | getD (Node(_, d, _, _)) = d;
    

fun rotateLeft (Node((Node(ll, ld, lh, lr)), d, h, r)) = let
  val nRt = Node(lr, d, maxH(getH(lr), getH(r)) + 1, r)
in
  Node(ll, ld, maxH(getH(ll), getH(nRt)) + 1, nRt)
end

fun rotateRight (Node(l, d, h, (Node(rl, rd, rh, rr)))) = let
  val nRt = Node(l, d, maxH(getH(l), getH(rl)) + 1, rl)
in
  Node(nRt, rd, maxH(getH(nRt), getH(rr)) + 1, rr)
end

fun doubleRotateLeft (Node(l, d, h, r)) = rotateLeft(Node(rotateRight(l), d, h, r));
fun doubleRotateRight (Node(l, d, h, r)) = rotateRight(Node(l, d, h, rotateLeft(r)));

fun balance Leaf = Leaf
  | balance (Node(l, d, h, r)) = let
            val rt = if getH(l) - getH(r) > 1 then
                        if getH(getL(l)) >= getH(getR(l)) then
                            rotateLeft(Node(l, d, h, r))
                        else doubleRotateLeft(Node(l, d, h, r))
                    else if getH(r) - getH(l) > 1 then
                        if getH(getR(r)) >= getH(getL(r)) then
                            rotateRight(Node(l, d, h, r))
                        else doubleRotateRight(Node(l, d, h, r))
                    else Node(l, d, h, r)
          in
            Node(getL(rt), getD(rt), maxH(getH(getL(rt)), getH(getR(rt))) + 1, getR(rt))
          end

fun insert (data, Leaf) = Node(Leaf, data, 0, Leaf)
  | insert (data, Node(l, d, h, r)) = let
    val rt = if d > data then Node(insert(data, l), d, h, r)
             else if d < data then Node(l, d, h, insert(data, r))
             else Node(l, d, h, r)
  in
    balance(rt)
  end


fun search (Leaf) data = 0
  | search (Node(l, d, h, r)) data = if (d = data) then 1
                                     else if (d > data) then search l data
                                     else search r data;

use "./input.sml";
val tree = foldl insert Leaf input;
val f = search tree;
val res = map f searchData;

fun printToFile(outFile: string, list: int list) =
  let
    val outStream = TextIO.openOut outFile
    fun out(xs : int list) =  
          case xs of
              [] => (TextIO.closeOut outStream)
            | x::xs' => (TextIO.output(outStream, (Int.toString x ^ "\n")); out(xs'))
  in
    out(list)
  end;
printToFile("./output.sml", res);
OS.Process.exit(OS.Process.success);