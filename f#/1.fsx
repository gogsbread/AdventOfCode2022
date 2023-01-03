#load "Common.fsx"

open Common
open System

// take a predicate and a list
// if list is empty just return
// if list is not empty then take while the predicate is true; and concatenate with the drop while the predicate is true

let p1 (input: List<string>) =
    input
    |> splitBy (fun s -> String.IsNullOrWhiteSpace s)
    |> List.map (fun l -> List.map int64 l)
    |> List.map (fun l -> List.sum l)
    |> List.max

let input = Common.readIn
input |> p1 |> Common.writeOut
