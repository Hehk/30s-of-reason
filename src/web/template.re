let globalStyles = "body { margin: 0; padding: 0;} input:focus{ box-shadow: 0 10px 40px 0 rgba(219,77,63,0.37), 0 2px
9px 0 rgba(219,77,63,0.36);}";

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

      <script src="assets/bundle.js"></script>
    </html>
|j};

let generateStyles = (~html="", ()) => {
  let css = Nice.extract(html).css |> List.fold_left((a, b) => a ++ b, "");
  {j|<style type="text/css">$globalStyles$css</style>|j}
};
