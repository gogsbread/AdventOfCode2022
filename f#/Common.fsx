module Common

open System

let rec splitBy (pred: 'a -> bool) (list: 'a list) =
    let index = list |> List.tryFindIndex pred

    match index with
    | Some i ->
        let (frnt, back) = List.splitAt i list
        frnt :: (splitBy pred back.Tail)
    | None -> [ list ]

let readIn =
    Seq.initInfinite (fun _ -> Console.ReadLine())
    |> Seq.takeWhile (fun line -> (not (isNull line)))
    |> Seq.toList

let writeOut output = printfn "%A" output
