let app = Express.App.make();

[@bs.module "body-parser"] external bodyParserJson : unit => Express.Middleware.t = "json";
let graphiqlMiddleware = ApolloServerExpress.createGraphiQLExpressMiddleware("/graphql");

let onListen = (port, e) =>
  switch e {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1)
  | _ => Js.log("Listening at localhost:" ++ string_of_int(port))
  };

let graphqlMiddleware = Router.GraphQL.make();
Express.App.use(app, bodyParserJson());
Express.App.useOnPath(app, graphqlMiddleware, ~path="/graphql");
Express.App.useOnPath(app, graphiqlMiddleware, ~path="/graphiql");
Express.App.listen(app, ~onListen=onListen(Config.env.port), ());
