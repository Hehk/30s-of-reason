let globalStyles = "body { margin: 0; padding: 0;}";

let make = (~body, ~styles, ~title, ()) => {j|
  <!DOCTYPE html>
    <html>
      <head>
        <title>$title</title>
        <link href="https://fonts.googleapis.com/css?family=Karla:400,700" rel="stylesheet">
        $styles
      </head>

      <body>
        <div id="react-root">$body</div>
      </body>

      <script src="dist/bundle.js"></script>
    </html>
|j};

let generateStyles = (~html="", ()) => {
  let css = Nice.extract(html).css |> List.fold_left((a, b) => a ++ b, "");
  {j|<style type="text/css">$globalStyles$css</style>|j}
};
