#load "Common.fsx"

open Common
open System

module p1 =
    let solve (input: List<string>) =
        input
        |> Seq.map (fun s ->
            if ((String.IsNullOrWhiteSpace >> not) s) then
                Some(int64 s)
            else
                None)
        |> Seq.fold
            (fun acc cal ->
                let (c, s) = acc

                match cal with
                | Some v -> (c + v, max (c + v) s)
                | None -> (0L, s))
            (0, 0)
        |> snd

let input = Common.readIn
input |> p1.solve |> Common.writeOut
