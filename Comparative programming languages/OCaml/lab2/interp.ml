(* $Id: interp.ml,v 1.9 2020-01-28 13:33:00-08 - - $ *)
(*David Grim
dgrim@ucsc.edu
CSE112*)

open Absyn;;

exception Unimplemented of string;;
let unimpl reason = raise (Unimplemented reason);;
let no_stmt reason continuation = raise (Unimplemented reason);;
let want_dump = ref false;;

let rec eval_expr (expr : Absyn.expr) : float = match expr with
    | Number number -> number
    | Memref memref -> (match memref with
      | Arrayref (ident, expr2) -> 
         (Hashtbl.find Tables.array_table ident).
          ((int_of_float (eval_expr expr2)))
      | Variable ident -> 
          (Hashtbl.find Tables.variable_table ident))
    | Unary (op, expr) -> 
        ((Hashtbl.find Tables.unary_fn_table op) (eval_expr expr)) 
    | Binary (op, expr1, expr2) ->
        ((Hashtbl.find Tables.binary_fn_table op) 
          (eval_expr expr1) (eval_expr expr2));;

let interp_print (print_list : Absyn.printable list) =
    let print_item item =
        (print_string " ";
         match item with
         | String str ->
           let regex = Str.regexp "\"\\(.*\\)\""
           in print_string (Str.replace_first regex "\\1" str)
         | Printexpr expr ->
           print_float (eval_expr expr))
    in (List.iter print_item print_list; print_newline());;

let interp_input (memref_list : Absyn.memref list) =
    let input_number memref = 
     try let number = Etc.read_number () 
      in match memref with
       | Variable var -> 
         Hashtbl.add Tables.variable_table var number
          | Arrayref (x, y) -> 
            let a = 
              (Hashtbl.find Tables.array_table x) in
                if((Array.length a) 
                  >(int_of_float (eval_expr y))) then
                  a.((int_of_float (eval_expr y)))
                  <- number
                else(raise)
                  (Unimplemented "Not in range")
        with End_of_file ->
          Hashtbl.replace Tables.variable_table "eof" 1.0
    in List.iter input_number memref_list;;


(*for bools*)
let eval_boolean_expr (expression : Absyn.expr ): 
bool = match expression with
    | Unary (op, expression)->false
    | Binary (op,x,y) -> ((Hashtbl.find Tables.binary_bool_table op) 
        (eval_expr x) (eval_expr y))
    | Number (num)->false
    | Memref (memref)->false;;

(*sb interpretation of goto*)
let interp_goto (label : Absyn.label) = 
    Hashtbl.find Tables.label_table label;;

(*sb interpretation of if*)
let interp_if ((x : Absyn.expr), (y : Absyn.label )) = 
    if (eval_boolean_expr x) 
    then Some(interp_goto y)
    else None;;

(*sb interpretation of dim*)
let interp_dim ((x : Absyn.ident), (y : Absyn.expr)) = 
    Hashtbl.replace Tables.array_table x 
        (Array.make (int_of_float (eval_expr y) 
        + 1)0.0);;

(*sb interpretation of let*)
let interp_let ((memref : Absyn.memref), 
    (expr: Absyn.expr)) = match memref with
    | Arrayref (x, y) -> 
      let a = (Hashtbl.find Tables.array_table x) in
        if((Array.length a) >= 
           (int_of_float (eval_expr y))) 
        then a.((int_of_float (eval_expr y))) <- (eval_expr expr)
        else raise(Unimplemented "Not in range")
    | Variable ident -> 
       (Hashtbl.add Tables.variable_table ident (eval_expr expr));;

let interp_stmt (statement : Absyn.stmt) :
    Absyn.program option = match statement with
    | Dim (ident, expr) -> (interp_dim (ident, expr); None) 
    | Let (memref, expr) -> (interp_let (memref, expr); None)
    | Goto label -> Some (interp_goto label)
    | If (expr, label) -> interp_if (expr, label)
    | Print print_list -> (interp_print print_list; None)
    | Input memref_list -> (interp_input memref_list; None);;

let rec interpret (program : Absyn.program) = match program with
    | [] -> ()
    | firstline::otherlines -> match firstline with
      | _, _, None -> interpret otherlines
      | _, _, Some stmt -> let next_line = interp_stmt stmt in
      match next_line with
      | None -> interpret otherlines
      | Some line -> interpret line ;;

let interpret_program program =
    (Tables.init_label_table program; 
     if !want_dump then Tables.dump_label_table ();
     if !want_dump then Dumper.dump_program program;
     interpret program);;
