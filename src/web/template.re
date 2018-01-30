let globalStyles = "body { margin: 0; padding: 0; background-color: rgb(219, 77, 63); }";

let make = (~body, ~styles, ~title, ()) => {j|
  <!DOCTYPE html>
    <html>
      <head>
        <title>$title</title>
        $styles
      </head>

      <body>
        <div id="root">$body</div>
      </body>
    </html>
|j};

let generateStyles = (~html="", ()) => {
  let css = Nice.extract(html).css |> List.fold_left((a, b) => a ++ b, "");
  {j|<style type="text/css">$globalStyles$css</style>|j}
};
