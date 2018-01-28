let app = Express.App.make();

[@bs.module "body-parser"]
external bodyParserJson : unit => Express.Middleware.t =
  "json";

let graphqlMiddleware = {
  let types = Snippet.graphQLType;
  let query = "type Query {\n    allSnippets(query: String): [Snippet]!\n    snippet(id: Int!): Snippet!\n  }";
  let snippet = Snippet.Handler.make();
  let resolvers = {"Query": Js.Obj.empty() |> Js.Obj.assign(snippet.queries)};
  GraphQLTools.makeExecutableSchema({
    "typeDefs": types ++ query,
    "resolvers": resolvers
  })
  |> ApolloServerExpress.createGraphQLExpressMiddleware
};

let graphiqlMiddleware =
  ApolloServerExpress.createGraphiQLExpressMiddleware("/graphql");

Express.App.use(app, bodyParserJson());

Express.App.useOnPath(app, graphqlMiddleware, ~path="/graphql");

Express.App.useOnPath(app, graphiqlMiddleware, ~path="/graphiql");

Express.App.useOnPath(
  app,
  Express.Middleware.from(
    (_req, res, _next) => {
      let body = ReactDOMServerRe.renderToString(<App />);
      Express.Response.sendString(res, Template.make(~body, ()))
    }
  ),
  ~path="/"
);

let onListen = (e) => {
  let port = string_of_int(Config.env.port);
  let message = {j|
  GraphQL  => localhost:$port/graphql
  GraphiQL => localhost:$port/graphiql
  Web      => localhost:$port/
  |j};
  switch e {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1)
  | _ => Js.log(message)
  }
};

Express.App.listen(app, ~onListen, ());
