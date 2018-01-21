open Express;

let makeSuccessJson = () => {
  let json = Js.Dict.empty();
  Js.Dict.set(json, "success", Js.Json.boolean(Js.true_));
  Js.Json.object_(json)
};

/* [checkProperty req next property k] makes sure [property] is
   present in [req]. If success then [k()] is invoked, otherwise
   [Next.route] is called with next */
let checkProperty = (req, next, property, k) => {
  let reqData = Request.asJsonObject(req);
  switch (Js.Dict.get(reqData, property)) {
  | None => next(Next.route)
  | Some(x) =>
    switch (Js.Json.decodeBoolean(x)) {
    | Some(b) when b == Js.true_ => k()
    | _ => next(Next.route)
    }
  }
};

/* same as [checkProperty] but with a list of properties */
let checkProperties = (req, next, properties, k) => {
  let rec aux = (properties) =>
    switch properties {
    | [] => k()
    | [p, ...tl] => checkProperty(req, next, p, () => aux(tl))
    };
  aux(properties)
};

let app = express();

App.useOnPath(app, ~path="/") @@
Middleware.from(
  (req, res, next) => {
    let previousMiddlewares = [];
    checkProperties(req, next, previousMiddlewares, () => Response.sendJson(res, makeSuccessJson()))
  }
);

let onListen = (port, e) =>
  switch e {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1)
  | _ => Js.log @@ "Listening at localhost:" ++ string_of_int(port)
  };

App.listen(app, ~onListen=onListen(3000), ());
