let app = Express.App.make();

[@bs.module "body-parser"] external bodyParserJson : unit => Express.Middleware.t = "json";

let graphqlMiddleware = {
  let types = Snippet.graphQLType;
  let query = "type Query {
    allSnippets(query: String): [Snippet]!
    snippet(id: Int!): Snippet!
  }";
  let snippet = Snippet.Handler.make();
  let resolvers = {"Query": Js.Obj.empty() |> Js.Obj.assign(snippet.queries)};
  GraphQLTools.makeExecutableSchema({"typeDefs": types ++ query, "resolvers": resolvers})
  |> ApolloServerExpress.createGraphQLExpressMiddleware
};

let graphiqlMiddleware = ApolloServerExpress.createGraphiQLExpressMiddleware("/graphql");

let onListen = (port, e) =>
  switch e {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1)
  | _ =>
    Js.log(
      "\n GraphQL  => localhost:"
      ++ string_of_int(port)
      ++ "/graphql\n GraphIQL => localhost:"
      ++ string_of_int(port)
      ++ "/graphiql\n"
    )
  };

Express.App.use(app, bodyParserJson());

Express.App.useOnPath(app, graphqlMiddleware, ~path="/graphql");

Express.App.useOnPath(app, graphiqlMiddleware, ~path="/graphiql");

Express.App.listen(app, ~onListen=onListen(Config.env.port), ());
