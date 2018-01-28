
let make = (~body="testing", ~title="", ()) => {j|
  <!DOCTYPE html>
    <html>
      <head>
        <title>$title</title>
        <link rel="stylesheet" href="/assets/index.css" />
      </head>
      
      <body>
        <div id="root">$body</div>
      </body>
    </html> 
|j};
